//
//  KDTree.h
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef RayTracer_KDTree_h
#define RayTracer_KDTree_h

#include "nvMath.h"
#include "HitInfo.h"
#include <vector>

template<typename T>
struct ptr
{
    static T* get(const T& obj) { return (T*)&obj; }
};

template<typename T>
struct ptr<T*>
{
    static T* get(T* obj) { return obj; }
};

inline void mergeBounds(nv::vec3f* b, const nv::vec3f* b1, const nv::vec3f* b2)
{
    b[0].x = b1[0].x < b2[0].x ? b1[0].x : b2[0].x;
    b[0].y = b1[0].y < b2[0].y ? b1[0].y : b2[0].y;
    b[0].z = b1[0].z < b2[0].z ? b1[0].z : b2[0].z;
    b[1].x = b1[1].x > b2[1].x ? b1[1].x : b2[1].x;
    b[1].y = b1[1].y > b2[1].y ? b1[1].y : b2[1].y;
    b[1].z = b1[1].z > b2[1].z ? b1[1].z : b2[1].z;
}

template<typename Ray, typename Geo> class KDTree
{
protected:
    struct KDTreeNode
    {
        nv::vec3f bounds[2];
        KDTreeNode* leftChild;
        KDTreeNode* rightChild;
        unsigned startIndex;
        unsigned num;
        
        KDTreeNode()
        {
            leftChild = rightChild = NULL;
        }
    };
    KDTreeNode* root;
    std::vector<Geo>* geoList;
    unsigned maxLeafElemNum;
    
    void nodeMergeBounds(KDTreeNode* node, const nv::vec3f* b1, const nv::vec3f* b2)
    {
        mergeBounds((nv::vec3f*)node->bounds, b1, b2);
    }
    
    void fillBounds(KDTreeNode* node)
    {
        node->bounds[0] = ptr<Geo>::get((*geoList)[node->startIndex])->getLowerBound();
        node->bounds[1] = ptr<Geo>::get((*geoList)[node->startIndex])->getUpperBound();
        for(unsigned i=node->startIndex+1; i<node->startIndex+node->num; i++)
        {
            nv::vec3f lb = ptr<Geo>::get((*geoList)[i])->getLowerBound();
            nv::vec3f ub = ptr<Geo>::get((*geoList)[i])->getUpperBound();
            node->bounds[0].x = node->bounds[0].x < lb.x ? node->bounds[0].x : lb.x;
            node->bounds[0].y = node->bounds[0].y < lb.y ? node->bounds[0].y : lb.y;
            node->bounds[0].z = node->bounds[0].z < lb.z ? node->bounds[0].z : lb.z;
            node->bounds[1].x = node->bounds[1].x > ub.x ? node->bounds[1].x : ub.x;
            node->bounds[1].y = node->bounds[1].y > ub.y ? node->bounds[1].y : ub.y;
            node->bounds[1].z = node->bounds[1].z > ub.z ? node->bounds[1].z : ub.z;
        }
    }
    
    static bool compareX(const Geo& g1, const Geo& g2)
    {
        float x1 = ptr<Geo>::get(g1)->getLowerBound().x+ptr<Geo>::get(g1)->getUpperBound().x;
        float x2 = ptr<Geo>::get(g2)->getLowerBound().x+ptr<Geo>::get(g2)->getUpperBound().x;
        return x1 < x2;
    }
    
    static bool compareY(const Geo& g1, const Geo& g2)
    {
        float y1 = ptr<Geo>::get(g1)->getLowerBound().y+ptr<Geo>::get(g1)->getUpperBound().y;
        float y2 = ptr<Geo>::get(g2)->getLowerBound().y+ptr<Geo>::get(g2)->getUpperBound().y;
        return y1 < y2;
    }
    
    static bool compareZ(const Geo& g1, const Geo& g2)
    {
        float z1 = ptr<Geo>::get(g1)->getLowerBound().z+ptr<Geo>::get(g1)->getUpperBound().z;
        float z2 = ptr<Geo>::get(g2)->getLowerBound().z+ptr<Geo>::get(g2)->getUpperBound().z;
        return z1 < z2;
    }
    
    void splitNode(KDTreeNode* node, int dim)
    {
        if(node->num <= maxLeafElemNum)
        {
            fillBounds(node);
            return;
        }
        
        switch (dim) {
            case 1:
                std::nth_element(geoList->begin()+node->startIndex,
                                 geoList->begin()+node->startIndex+node->num/2,
                                 geoList->begin()+node->startIndex+node->num, compareY);
                break;
            case 2:
                std::nth_element(geoList->begin()+node->startIndex,
                                 geoList->begin()+node->startIndex+node->num/2,
                                 geoList->begin()+node->startIndex+node->num, compareZ);
                break;
            default:
                std::nth_element(geoList->begin()+node->startIndex,
                                 geoList->begin()+node->startIndex+node->num/2,
                                 geoList->begin()+node->startIndex+node->num, compareX);
                break;
        }
        node->leftChild = new KDTreeNode;
        node->leftChild->startIndex = node->startIndex;
        node->leftChild->num = node->num/2;
        
        node->rightChild = new KDTreeNode;
        node->rightChild->startIndex = node->startIndex + node->num/2;
        node->rightChild->num = node->num - node->num/2;
        
        splitNode(node->leftChild, (dim+1)%3);
        splitNode(node->rightChild, (dim+1)%3);
        
        nodeMergeBounds(node, node->leftChild->bounds, node->rightChild->bounds);
    }
    
    inline bool intersectBB(const Ray& ray, nv::vec3f bounds[2]) const
    {
        nv::vec3f invdir = 1.0 / ray.getDir();
        
        int s0 = invdir.x < 0;
        int s1 = invdir.y < 0;
        int s2 = invdir.z < 0;
        
        float tmin, tmax, tymin, tymax, tzmin, tzmax;
        tmin = (bounds[s0].x - ray.getOrig().x) * invdir.x;
        tmax = (bounds[1-s0].x - ray.getOrig().x) * invdir.x;
        tymin = (bounds[s1].y - ray.getOrig().y) * invdir.y;
        tymax = (bounds[1-s1].y - ray.getOrig().y) * invdir.y;
        if ((tmin > tymax) || (tymin > tmax))
            return false;
        if (tymin > tmin)
            tmin = tymin;
        if (tymax < tmax)
            tmax = tymax;
        tzmin = (bounds[s2].z - ray.getOrig().z) * invdir.z;
        tzmax = (bounds[1-s2].z - ray.getOrig().z) * invdir.z;
        if ((tmin > tzmax) || (tzmin > tmax))
            return false;
        if (tzmin > tmin)
            tmin = tzmin;
        if (tzmax < tmax)
            tmax = tzmax;
        
        if(tmax < 0)
            return false;
        
        return true;
    }
    
    void clearNode(KDTreeNode* node)
    {
        if(!node)
            return;
        if(node->leftChild)
            clearNode(node->leftChild);
        if(node->rightChild)
            clearNode(node->rightChild);
        delete node;
    }
    
    HitInfo intersectNode(KDTreeNode* node, const Ray& ray) const
    {
        if(!intersectBB(ray, node->bounds))
            return HitInfo();
        if(node->leftChild == NULL)
        {
            HitInfo info;
            for(unsigned i=node->startIndex; i<node->startIndex+node->num; i++)
            {
                HitInfo newInfo = ptr<Geo>::get((*geoList)[i])->intersect(ray);
                if(newInfo.dist < info.dist)
                {
                    info = newInfo;
                    info.index = i;
                }
            }
            return info;
        }
        HitInfo lInfo = intersectNode(node->leftChild, ray);
        HitInfo rInfo = intersectNode(node->rightChild, ray);
        if(lInfo.dist < rInfo.dist)
            return lInfo;
        return rInfo;
    }
public:
    void clear()
    {
        geoList = NULL;
        clearNode(root);
        root = NULL;
    }
    nv::vec3f getLowerBound() { return root ? root->bounds[0] : nv::vec3f(); }
    nv::vec3f getUpperBound() { return root ? root->bounds[1] : nv::vec3f(); }
    KDTree()
    {
        root = NULL;
        maxLeafElemNum = 1;
        clear();
    }
    void build(std::vector<Geo>& geoList, unsigned maxLeafElemNum = 1)
    {
        clear();
        this->geoList = &geoList;
        this->maxLeafElemNum = maxLeafElemNum;
        root = new KDTreeNode;
        root->startIndex = 0;
        root->num = unsigned(geoList.size());
        splitNode(root, 0);
    }
    HitInfo intersect(const Ray& ray) const
    {
        return intersectNode(root, ray);
    }
};

#endif

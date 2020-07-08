/*
 * Copyright (c) 2017
 * FZI Forschungszentrum Informatik, Karlsruhe, Germany (www.fzi.de)
 * KIT, Institute of Measurement and Control, Karlsruhe, Germany (www.mrt.kit.edu)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include <OGRE/OgreAny.h>
#include <OGRE/OgreMaterial.h>
#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSharedPtr.h>
#include <OGRE/OgreVector3.h>
#include <rviz/ogre_helpers/object.h>
#include <rviz/ogre_helpers/shape.h>

#include "util_rviz.hpp"


namespace Ogre {
class Vector3;
class SceneNode;
class SceneManager;
class ColourValue;
class Quaternion;
class Any;
class Entity;
} // namespace Ogre

namespace rviz {
typedef std::vector<std::shared_ptr<Shape>> shape_vector;

class MultiShape : public Object {
public:
    MultiShape(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node = NULL);
    virtual ~MultiShape();

    // overrides from rviz:Object

    /**
     * \brief Sets the object visible or not.
     */
    void visible(bool vis);

    /**
     * \brief Set the same color to all shapes of this object.
     */
    virtual void setColor(float r, float g, float b, float a);

    /**
     * \brief Set the same color to all shapes of this object.
     */
    void setColor(const Ogre::ColourValue& c);

    /**
     * \brief Set the position of this objects scene node.
     */
    virtual void setPosition(const Ogre::Vector3& position);

    /**
     * \brief Set the orientation of this objects scene node.
     */
    virtual void setOrientation(const Ogre::Quaternion& orientation);

    /**
     * \brief Set the scale of this objects scene node.
     */
    virtual void setScale(const Ogre::Vector3& scale);

    /**
     * \brief Set user data to all ogre objects owned by this object.
     * The user data is forwarded to the Ogre::MovableObject::setUserAny() method of the shapes entities in the
     * shapes_vector.
     */
    virtual void setUserData(const Ogre::Any& data);

    /**
     * \brief Get the position of the scene node for this object.
     *
     * @return The the position of the scene node.
     */
    virtual const Ogre::Vector3& getPosition();

    /**
     * \brief Get the orientation of the scene node for this object.
     *
     * @return The the orientation of the scene node.
     */
    virtual const Ogre::Quaternion& getOrientation();

    /**
     * \brief Get the root scene node for this object
     *
     * @return The root scene node of this object
     */
    Ogre::SceneNode* getRootNode() {
        return scene_node_;
    }

    /**
     * \brief Get a Vector of all shapes in this node
     *
     * @return The shapes_ vector of this node node of this object
     */
    virtual shape_vector* getShapes() {
        return &shapes_;
    }

    /**
     * \brief Get a vector of all entities owned by this object.
     * Calls the shape's getEntity() method.
     *
     * @return vector of all entities.
     */
    virtual std::vector<Ogre::Entity*> getEntities();

    /**
     * \brief Get a vector of all materials used by shapes owned by this object.
     * Calls the shape's getMaterial() method.
     *
     * @return vector of all used materials.
     */
    virtual std::vector<Ogre::MaterialPtr> getMaterials();

    /**
     * \brief Get a vector of all types of the entities owned by this object.
     * Calls the shape's getType() method.
     *
     * @return vector of all types.
     */
    virtual std::vector<Shape::Type> getTypes();

protected:
    Ogre::SceneNode* scene_node_;
    shape_vector shapes_;
};

class SimpleCar : public MultiShape {
public:
    SimpleCar(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node = NULL);
    void setColorPartly(float r, float g, float b, float a);
    void setColorPartly(const Ogre::ColourValue& c);

protected:
    void renewShapesVec();
    shape_vector coloredShapes_;
    shape_vector blackShapes_;
};

class SimplePedestrian : public MultiShape {
public:
    SimplePedestrian(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node = NULL);
};

class SimpleBike : public MultiShape {
public:
    SimpleBike(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node = NULL);
};

class SimpleUnknown : public MultiShape {
public:
    SimpleUnknown(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node = NULL);
};

} // namespace rviz

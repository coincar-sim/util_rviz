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

#include "util_rvizshapes.hpp"

namespace rviz {

MultiShape::MultiShape(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node) : Object(scene_manager) {
    if (!parent_node) {
        parent_node = scene_manager_->getRootSceneNode();
    }
    scene_node_ = parent_node->createChildSceneNode();
}


MultiShape::~MultiShape() {
    scene_manager_->destroySceneNode(scene_node_->getName());
}
void MultiShape::visible(bool vis) {
    scene_node_->setVisible(vis);
}
void MultiShape::setColor(float r, float g, float b, float a) {
    MultiShape::setColor(Ogre::ColourValue(r, g, b, a));
}

void MultiShape::setColor(const Ogre::ColourValue& c) {
    for (auto s : shapes_) {
        s->setColor(c);
    }
}
void MultiShape::setPosition(const Ogre::Vector3& position) {
    util_rviz::setPositionSafely(scene_node_, position);
}
void MultiShape::setOrientation(const Ogre::Quaternion& orientation) {
    util_rviz::setOrientationSafely(scene_node_, orientation);
}
void MultiShape::setScale(const Ogre::Vector3& scale) {
    scene_node_->setScale(scale);
}
void MultiShape::setUserData(const Ogre::Any& data) {
    for (auto s : shapes_) {
        s->setUserData(data);
    }
}
const Ogre::Vector3& MultiShape::getPosition() {
    return scene_node_->getPosition();
}
const Ogre::Quaternion& MultiShape::getOrientation() {
    return scene_node_->getOrientation();
}
std::vector<Ogre::Entity*> MultiShape::getEntities() {
    std::vector<Ogre::Entity*> entities;
    for (auto s : shapes_) {
        entities.push_back(s->getEntity());
    }
    return entities;
}
std::vector<Ogre::MaterialPtr> MultiShape::getMaterials() {
    std::vector<Ogre::MaterialPtr> materials;
    for (auto s : shapes_) {
        materials.push_back(s->getMaterial());
    }
    return materials;
}
std::vector<Shape::Type> MultiShape::getTypes() {
    std::vector<Shape::Type> types;
    for (auto s : shapes_) {
        types.push_back(s->getType());
    }
    return types;
}

SimpleCar::SimpleCar(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node)
        : MultiShape(scene_manager, parent_node) {

    // BEGIN: Definition of Objects geometric visual appearance
    float wheelDiameter = 0.8;
    float wheelWidth = 0.4;
    Ogre::Vector3 wheelScale(wheelDiameter, wheelWidth, wheelDiameter);
    Ogre::Vector3 wheelPosition(0.0, 0.0, wheelScale.z / 2.0);

    std::shared_ptr<rviz::Shape> lower_cube =
        std::make_shared<rviz::Shape>(Shape::Cylinder, scene_manager_, scene_node_);
    Ogre::Vector3 lowerCubeScale(4, 1.8, 0.8);
    lower_cube->setScale(lowerCubeScale);
    Ogre::Vector3 lowerCubePosition(0, 0, lowerCubeScale.z / 2.0 + wheelScale.z / 2.0);
    lower_cube->setPosition(lowerCubePosition);
    coloredShapes_.push_back(lower_cube);

    std::shared_ptr<rviz::Shape> upper_cube =
        std::make_shared<rviz::Shape>(rviz::Shape::Cube, scene_manager_, scene_node_);
    Ogre::Vector3 upperCubeScale(2, 1.8, 0.8);
    upper_cube->setScale(upperCubeScale);
    Ogre::Vector3 upperCubePosition(0, 0, lowerCubeScale.z + upperCubeScale.z / 2.0 + wheelScale.z / 2.0);
    upper_cube->setPosition(upperCubePosition);
    coloredShapes_.push_back(upper_cube);

    std::shared_ptr<rviz::Shape> wheel_fr =
        std::make_shared<rviz::Shape>(rviz::Shape::Cylinder, scene_manager_, scene_node_);
    wheel_fr->setPosition(wheelPosition);
    wheel_fr->setColor(0.0, 0.0, 0.0, 1.0);
    wheel_fr->setScale(wheelScale);
    Ogre::Vector3 wheelFROffset(1.4 / wheelScale.x, -lowerCubeScale.y / 2.0 / wheelScale.y, 0.0);
    wheel_fr->setOffset(wheelFROffset);
    blackShapes_.push_back(wheel_fr);

    std::shared_ptr<rviz::Shape> wheel_fl =
        std::make_shared<rviz::Shape>(rviz::Shape::Cylinder, scene_manager_, scene_node_);
    wheel_fl->setPosition(wheelPosition);
    wheel_fl->setColor(0.0, 0.0, 0.0, 1.0);
    wheel_fl->setScale(wheelScale);
    Ogre::Vector3 wheelFLOffset(1.4 / wheelScale.x, lowerCubeScale.y / 2.0 / wheelScale.y, 0.0);
    wheel_fl->setOffset(wheelFLOffset);
    blackShapes_.push_back(wheel_fl);

    std::shared_ptr<rviz::Shape> wheel_br =
        std::make_shared<rviz::Shape>(rviz::Shape::Cylinder, scene_manager_, scene_node_);
    wheel_br->setPosition(wheelPosition);
    wheel_br->setColor(0.0, 0.0, 0.0, 1.0);
    wheel_br->setScale(wheelScale);
    Ogre::Vector3 wheelBROffset(-1.4 / wheelScale.x, -lowerCubeScale.y / 2.0 / wheelScale.y, 0.0);
    wheel_br->setOffset(wheelBROffset);
    blackShapes_.push_back(wheel_br);

    std::shared_ptr<rviz::Shape> wheel_bl =
        std::make_shared<rviz::Shape>(rviz::Shape::Cylinder, scene_manager_, scene_node_);
    wheel_bl->setPosition(wheelPosition);
    wheel_bl->setColor(0.0, 0.0, 0.0, 1.0);
    wheel_bl->setScale(wheelScale);
    Ogre::Vector3 wheelBLOffset(-1.4 / wheelScale.x, lowerCubeScale.y / 2.0 / wheelScale.y, 0.0);
    wheel_bl->setOffset(wheelBLOffset);
    blackShapes_.push_back(wheel_bl);
    // END: Definition of Objects geometric visual appearance

    renewShapesVec();
}

void SimpleCar::setColorPartly(float r, float g, float b, float a) {
    SimpleCar::setColorPartly(Ogre::ColourValue(r, g, b, a));
}

void SimpleCar::setColorPartly(const Ogre::ColourValue& c) {
    for (auto s : coloredShapes_) {
        s->setColor(c);
    }
    for (auto s : blackShapes_) {
        s->setColor(Ogre::ColourValue(0.0, 0.0, 0.0, c.a));
    }
    renewShapesVec();
}

void SimpleCar::renewShapesVec() {
    shapes_.clear();
    auto iter = shapes_.begin();
    shapes_.insert(iter, blackShapes_.begin(), blackShapes_.end());
    iter = shapes_.end();
    shapes_.insert(iter, coloredShapes_.begin(), coloredShapes_.end());
}

SimplePedestrian::SimplePedestrian(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node)
        : MultiShape(scene_manager, parent_node) {

    float corpusHeight = 1.6;
    float pedestrianWidth = 0.7;

    std::shared_ptr<rviz::Shape> corpus = std::make_shared<rviz::Shape>(Shape::Cylinder, scene_manager_, scene_node_);
    Ogre::Vector3 corpusScale(pedestrianWidth, corpusHeight, pedestrianWidth);
    corpus->setScale(corpusScale);
    Ogre::Vector3 corpusPosition(0, 0, corpusHeight / 2.0);
    corpus->setPosition(corpusPosition);
    Ogre::Quaternion corpusOrientation(std::sqrt(0.5), std::sqrt(0.5), 0, 0);
    corpus->setOrientation(corpusOrientation);
    shapes_.push_back(corpus);

    std::shared_ptr<rviz::Shape> head = std::make_shared<rviz::Shape>(Shape::Sphere, scene_manager_, scene_node_);
    Ogre::Vector3 sphereScale(pedestrianWidth, pedestrianWidth, pedestrianWidth);
    head->setScale(sphereScale);
    Ogre::Vector3 spherePosition(0, 0, corpusHeight + pedestrianWidth / 2.0);
    head->setPosition(spherePosition);
    shapes_.push_back(head);
}

SimpleBike::SimpleBike(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node)
        : MultiShape(scene_manager, parent_node) {

    float wheelDiameter = 1.4;
    float wheelWidth = 0.7;
    Ogre::Vector3 wheelScale(wheelDiameter, wheelWidth, wheelDiameter);
    Ogre::Vector3 wheelPosition(0.0, 0.0, wheelScale.z / 2.0);

    std::shared_ptr<rviz::Shape> lower_cube =
        std::make_shared<rviz::Shape>(Shape::Cylinder, scene_manager_, scene_node_);
    // (length, width, height)
    Ogre::Vector3 lowerCubeScale(3, 0.6, 0.8);
    lower_cube->setScale(lowerCubeScale);
    Ogre::Vector3 lowerCubePosition(0, 0, lowerCubeScale.z / 2.0 + wheelScale.z / 2.0);
    lower_cube->setPosition(lowerCubePosition);
    shapes_.push_back(lower_cube);

    std::shared_ptr<rviz::Shape> wheel_f =
        std::make_shared<rviz::Shape>(rviz::Shape::Cylinder, scene_manager_, scene_node_);
    wheel_f->setPosition(wheelPosition);
    wheel_f->setColor(0.0, 0.0, 0.0, 1.0);
    wheel_f->setScale(wheelScale);
    Ogre::Vector3 wheelFOffset(1.4 / wheelScale.x, 0.0, 0.0);
    wheel_f->setOffset(wheelFOffset);
    shapes_.push_back(wheel_f);

    std::shared_ptr<rviz::Shape> wheel_b =
        std::make_shared<rviz::Shape>(rviz::Shape::Cylinder, scene_manager_, scene_node_);
    wheel_b->setPosition(wheelPosition);
    wheel_b->setColor(0.0, 0.0, 0.0, 1.0);
    wheel_b->setScale(wheelScale);
    Ogre::Vector3 wheelBOffset(-1.4 / wheelScale.x, 0.0, 0.0);
    wheel_b->setOffset(wheelBOffset);
    shapes_.push_back(wheel_b);

    float corpusHeight = 1.6;
    float pedestrianWidth = 0.7;

    std::shared_ptr<rviz::Shape> corpus = std::make_shared<rviz::Shape>(Shape::Cylinder, scene_manager_, scene_node_);
    Ogre::Vector3 corpusScale(pedestrianWidth, corpusHeight, pedestrianWidth);
    corpus->setScale(corpusScale);
    Ogre::Vector3 corpusPosition(0, 0, corpusHeight / 2.0);
    corpus->setPosition(corpusPosition);
    Ogre::Quaternion corpusOrientation(std::sqrt(0.5), std::sqrt(0.5), 0, 0);
    corpus->setOrientation(corpusOrientation);
    shapes_.push_back(corpus);

    std::shared_ptr<rviz::Shape> head = std::make_shared<rviz::Shape>(Shape::Sphere, scene_manager_, scene_node_);
    Ogre::Vector3 sphereScale(pedestrianWidth, pedestrianWidth, pedestrianWidth);
    head->setScale(sphereScale);
    Ogre::Vector3 spherePosition(0, 0, corpusHeight + pedestrianWidth / 2.0);
    head->setPosition(spherePosition);
    shapes_.push_back(head);
}

SimpleUnknown::SimpleUnknown(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node)
        : MultiShape(scene_manager, parent_node) {
    std::shared_ptr<rviz::Shape> cube = std::make_shared<rviz::Shape>(rviz::Shape::Cube, scene_manager_, scene_node_);
    Ogre::Vector3 cubeScale(1.0, 1.0, 1.0);
    cube->setScale(cubeScale);
    Ogre::Vector3 cubePosition(0.0, 0.0, cubeScale.z / 2.0);
    cube->setPosition(cubePosition);
    shapes_.push_back(cube);
}

} // end namespace rviz

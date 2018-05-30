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

#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreVector3.h>
#include <ros/ros.h>


namespace {
/* Type Traits for Pointer Like types. Covering Raw Pointers, std-smart pointers and boost smart pointers */
template <class T>
struct is_pointer_type_helper : std::false_type {};
template <class T>
struct is_pointer_type_helper<T*> : std::true_type {};
template <class T>
struct is_pointer_type_helper<std::shared_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<std::shared_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<std::unique_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<std::unique_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<std::weak_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<std::weak_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::shared_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::shared_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::scoped_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::scoped_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::weak_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::weak_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::intrusive_ptr<T>> : std::true_type {};
template <class T>
struct is_pointer_type_helper<boost::intrusive_ptr<T const>> : std::true_type {};
template <class T>
struct is_pointer_type : is_pointer_type_helper<typename std::remove_cv<T>::type> {};

/* Helper Functions to Handle Reference, Pointer and SmartPointer Types in the Templates
 * Returns a pointer like type
 * Covering Raw Pointers, std smart pointers and boost smart pointers
 */
// Reference into Pointer
template <typename T>
T* ptr(T& obj) {
    return &obj;
}
// Object is already Pointer
template <typename T>
T* ptr(T* obj) {
    return obj;
}
// Object is already (smart) Pointer
template <typename T>
std::shared_ptr<T> ptr(std::shared_ptr<T> obj) {
    return obj;
}
// Object is already (smart) Pointer
template <typename T>
std::unique_ptr<T> ptr(std::unique_ptr<T> obj) {
    return obj;
}
// Object is already (smart) Pointer
template <typename T>
std::weak_ptr<T> ptr(std::weak_ptr<T> obj) {
    return obj;
}
// Object is already (smart) Pointer
template <typename T>
boost::shared_ptr<T> ptr(boost::shared_ptr<T> obj) {
    return obj;
} // Object is already (smart) Pointer
template <typename T>
boost::scoped_ptr<T> ptr(boost::scoped_ptr<T> obj) {
    return obj;
}
// Object is already (smart) Pointer
template <typename T>
boost::weak_ptr<T> ptr(boost::weak_ptr<T> obj) {
    return obj;
}
// Object is already (smart) Pointer
template <typename T>
boost::intrusive_ptr<T> ptr(boost::intrusive_ptr<T> obj) {
    return obj;
}
} // end namespace


namespace util_rviz {

template <typename T>
void setPositionSafely(T& settableObject, const Ogre::Vector3& position) {
    if (ptr(settableObject) && !position.isNaN()) {
        ptr(settableObject)->setPosition(position);
    } else {
        if (position.isNaN()) {
            ROS_ERROR_THROTTLE(1, "Could not set position. Position is not valid (NAN).");
        } else {
            ROS_ERROR_THROTTLE(1, "Could not set position.");
        }
    }
}

template <typename T>
void setOrientationSafely(T& settableObject, const Ogre::Quaternion& orientation) {
    if (ptr(settableObject) && !orientation.isNaN()) {
        ptr(settableObject)->setOrientation(orientation);
    } else {
        if (orientation.isNaN()) {
            ROS_ERROR_THROTTLE(1, "Could not set position. Orientation is not valid (NAN).");
        } else {
            ROS_ERROR_THROTTLE(1, "Could not set position.");
        }
    }
}

} // namespace util_rviz

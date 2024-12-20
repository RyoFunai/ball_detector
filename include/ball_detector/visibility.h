// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BALL_DETETOR__VISIBILITY_H_
#define BALL_DETETOR__VISIBILITY_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__

#ifdef __GNUC__
#define BALL_DETETOR_EXPORT __attribute__((dllexport))
#define BALL_DETETOR_IMPORT __attribute__((dllimport))
#else
#define BALL_DETETOR_EXPORT __declspec(dllexport)
#define BALL_DETETOR_IMPORT __declspec(dllimport)
#endif

#ifdef BALL_DETETOR_DLL
#define BALL_DETECTOR_PUBLIC BALL_DETETOR_EXPORT
#else
#define BALL_DETECTOR_PUBLIC BALL_DETETOR_IMPORT
#endif

#define BALL_DETECTOR_PUBLIC_TYPE BALL_DETECTOR_PUBLIC

#define BALL_DETETOR_LOCAL

#else

#define BALL_DETETOR_EXPORT __attribute__((visibility("default")))
#define BALL_DETETOR_IMPORT

#if __GNUC__ >= 4
#define BALL_DETECTOR_PUBLIC __attribute__((visibility("default")))
#define BALL_DETETOR_LOCAL __attribute__((visibility("hidden")))
#else
#define BALL_DETECTOR_PUBLIC
#define BALL_DETETOR_LOCAL
#endif

#define BALL_DETECTOR_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif // BALL_DETETOR__VISIBILITY_H_
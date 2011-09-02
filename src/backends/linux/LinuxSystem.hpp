/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP
#define GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP

#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/implementation/ThreadFactory.hpp>

class Runnable;

namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxSystem  : public gdx_cpp::implementation::System
{
class LinuxThreadFactory : public gdx_cpp::implementation::ThreadFactory {
public: 
        implementation::Thread::ptr createThread(Runnable* t);
};

class LinuxMutexFactory : public gdx_cpp::implementation::MutexFactory {
public:
        implementation::Mutex::ptr createMutex();
};

public:
    int64_t nanoTime();

    LinuxThreadFactory* getThreadFactory() {
        return &threadFactory;
    }

    LinuxMutexFactory* getMutexFactory() {
        return &mutexFactory;
    }
    
private:
    LinuxThreadFactory threadFactory;
    LinuxMutexFactory mutexFactory;
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP
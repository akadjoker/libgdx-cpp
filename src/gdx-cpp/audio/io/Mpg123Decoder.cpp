
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "Mpg123Decoder.hpp"

using namespace gdx_cpp::audio::io;

int Mpg123Decoder::readSamples (const ShortBuffer& samples) {
    int read = readSamples(handle, samples, samples.capacity());
    samples.position(0);
    return read;
}

int Mpg123Decoder::skipSamples (int numSamples) {
    return skipSamples(handle, numSamples);
}

int Mpg123Decoder::getNumChannels () {
    return getNumChannels(handle);
}

int Mpg123Decoder::getRate () {
    return getRate(handle);
}

float Mpg123Decoder::getLength () {
    return getLength(handle);
}

void Mpg123Decoder::dispose () {
    closeFile(handle);
}

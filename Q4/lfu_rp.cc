root@0860e38bc49f:/home/gen5-525ce650e1a5bbe71c39d4b15598d6c003cc9f9e/src/mem/cache/replacement_policies# cat lfu_rp.cc 
/**
 * Copyright (c) 2018 Inria
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Daniel Carvalho
 */

#include "mem/cache/replacement_policies/lfu_rp.hh"

#include <cassert>
#include <memory>

#include "params/LFURP.hh"

LFURP::LFURP(const Params *p)
    : BaseReplacementPolicy(p)
{
}

void
LFURP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
const
{
    // Reset reference count
    std::static_pointer_cast<LFUReplData>(replacement_data)->refCount = 0;
}

void
LFURP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Update reference count
    std::static_pointer_cast<LFUReplData>(replacement_data)->refCount++;
}

void
LFURP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Reset reference count
    std::static_pointer_cast<LFUReplData>(replacement_data)->refCount = 1;
}

ReplaceableEntry*
LFURP::getVictim(const ReplacementCandidates& candidates) const
{
     // ReplaceableEntry* arr[1000];
     // int  start_index=0, end_index=0, old_index=0;

    // There must be at least one replacement candidate
    assert(candidates.size() > 0);

    // Visit all candidates to find victim
    ReplaceableEntry* victim = candidates[0];
    
    for (const auto& candidate : candidates) {
        // Update victim entry if necessary
        if (std::static_pointer_cast<LFUReplData>(
                    candidate->replacementData)->refCount <
                std::static_pointer_cast<LFUReplData>(
                    victim->replacementData)->refCount) {
           
            victim = candidate;

        }else if (std::static_pointer_cast<LFUReplData>(
                    candidate->replacementData)->refCount ==
                std::static_pointer_cast<LFUReplData>(
                    victim->replacementData)->refCount){
            // find a victim from a list of same frequency candidates
            auto candidate_var = std::static_pointer_cast<LFUReplData>(
                    candidate->replacementData);
          
            if(std::static_pointer_cast<LFUReplData>(
                    candidate->replacementData)->refCount <
                std::static_pointer_cast<LFUReplData>(
                    victim->replacementData)->refCount){
                    victim = candidate;
            }
     
        }
    }
    
 
    return victim;
}

std::shared_ptr<ReplacementData>
LFURP::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new LFUReplData());
}

LFURP*
LFURPParams::create()
{
    return new LFURP(this);
}

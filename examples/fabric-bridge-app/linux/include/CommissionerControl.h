/*
 *
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#pragma once

#include <app/clusters/commissioner-control-server/commissioner-control-server.h>
#include <app/util/af-types.h>
#include <lib/core/CHIPError.h>

namespace chip {
namespace app {
namespace Clusters {
namespace CommissionerControl {

class CommissionerControlDelegate : public Delegate
{
public:
    CHIP_ERROR HandleCommissioningApprovalRequest(const CommissioningApprovalRequest & request) override;
    CHIP_ERROR ValidateCommissionNodeCommand(NodeId clientNodeId, uint64_t requestId) override;
    CHIP_ERROR GetCommissioningWindowParams(CommissioningWindowParams & outParams) override;
    CHIP_ERROR HandleCommissionNode(const CommissioningWindowParams & params, const Optional<ByteSpan> & ipAddress,
                                    const Optional<uint16_t> & port) override;

    ~CommissionerControlDelegate() = default;

private:
    static constexpr size_t kLabelBufferSize = 64;

    uint64_t mRequestId  = 0;
    NodeId mClientNodeId = kUndefinedNodeId;
    VendorId mVendorId   = VendorId::Unspecified;
    uint16_t mProductId  = 0;
    char mLabelBuffer[kLabelBufferSize + 1];
    Optional<CharSpan> mLabel;

    // Parameters needed for non-basic commissioning.
    uint8_t mPBKDFSaltBuffer[Crypto::kSpake2p_Max_PBKDF_Salt_Length];
    ByteSpan mPBKDFSalt;
    Crypto::Spake2pVerifierSerialized mPAKEPasscodeVerifierBuffer;
    ByteSpan mPAKEPasscodeVerifier;
};

} // namespace CommissionerControl
} // namespace Clusters
} // namespace app
} // namespace chip

CHIP_ERROR CommissionerControlInit();
CHIP_ERROR CommissionerControlShutdown();

/********************************************************************************
 * Copyright (c) 2025 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef SCORE_MW_DIAG_UDS_TYPES_H
#define SCORE_MW_DIAG_UDS_TYPES_H

#include <cstdint>

namespace mw::diag::uds {

/// @brief UDS negative response codes (NRC)
/// @details Standard UDS response codes as defined in ISO 14229-1
enum class UDSResponseCode : std::uint8_t {
    kGeneralReject = 0x10,
    kServiceNotSupported = 0x11,
    kSubFunctionNotSupported = 0x12,
    kIncorrectMessageLengthOrInvalidFormat = 0x13,
    kResponseTooLong = 0x14,
    kBusyRepeatRequest = 0x21,
    kConditionsNotCorrect = 0x22,
    kNoResponseFromSubnetComponent = 0x23,
    kRequestSequenceError = 0x24,
    kNoResponseFromSubNetComponent = 0x25,
    kFailurePreventsExecutionOfRequestedAction = 0x26,
    kRequestOutOfRange = 0x31,
    kSecurityAccessDenied = 0x33,
    kAuthenticationRequired = 0x34,
    kInvalidKey = 0x35,
    kExceededNumberOfAttempts = 0x36,
    kRequiredTimeDelayNotExpired = 0x37,
    kSecureDataTransmissionRequired = 0x38,
    kSecureDataTransmissionNotAllowed = 0x39,
    kSecureDataVerificationFailed = 0x3A,
    kCertificateVerificationFailed_InvalidTimePeriod = 0x50,
    kCertificateVerificationFailed_InvalidSignature = 0x51,
    kCertificateVerificationFailed_InvalidChainOfTrust = 0x52,
    kCertificateVerificationFailed_InvalidType = 0x53,
    kCertificateVerificationFailed_InvalidFormat = 0x54,
    kCertificateVerificationFailed_InvalidContent = 0x55,
    kCertificateVerificationFailed_InvalidScope = 0x56,
    kCertificateVerificationFailed_InvalidCertificate = 0x57,
    kOwnershipVerificationFailed = 0x58,
    kChallengeCalculationFailed = 0x59,
    kSettingAccessRightsFailed = 0x5A,
    kSessionKeyCreationOrDerivationFailed = 0x5B,
    kConfigurationDataUsageFailed = 0x5C,
    kDeAuthenticationFailed = 0x5D,
    kUploadDownloadNotAccepted = 0x70,
    kTransferDataSuspended = 0x71,
    kGeneralProgrammingFailure = 0x72,
    kWrongBlockSequenceCounter = 0x73,
    kRequestCorrectlyReceived_ResponsePending = 0x78,
    kSubFunctionNotSupportedInActiveSession = 0x7E,
    kServiceNotSupportedInActiveSession = 0x7F,
    kRpmTooHigh = 0x81,
    kRpmTooLow = 0x82,
    kEngineIsRunning = 0x83,
    kEngineIsNotRunning = 0x84,
    kEngineRunTimeTooLow = 0x85,
    kTemperatureTooHigh = 0x86,
    kTemperatureTooLow = 0x87,
    kVehicleSpeedTooHigh = 0x88,
    kVehicleSpeedTooLow = 0x89,
    kThrottleOrPedalTooHigh = 0x8A,
    kThrottleOrPedalTooLow = 0x8B,
    kTransmissionRangeNotInNeutral = 0x8C,
    kTransmissionRangeNotInGear = 0x8D,
    kBrakeSwitchOrSwitchesNotClosed = 0x8F,
    kShifterLeverNotInPark = 0x90,
    kTorqueConvertClutchLocked = 0x91,
    kVoltageTooHigh = 0x92,
    kVoltageTooLow = 0x93,
    kResourceTemporarilyNotAvailable = 0x94
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_TYPES_H

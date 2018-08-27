#pragma once

#include "extern/cdmapi.h"
using namespace cdm;

class CDMProxy_9 : ContentDecryptionModule_9 {
private:
    ContentDecryptionModule_9 *orig_cdm;

public:
    explicit CDMProxy_9(ContentDecryptionModule_9 *passed_cdm);
    ~CDMProxy_9() override = default;


    void Initialize(bool allow_distinctive_identifier,
                            bool allow_persistent_state) override;

    void GetStatusForPolicy(uint32_t promise_id,
                                    const Policy& policy) override;


    void SetServerCertificate(uint32_t promise_id,
                                      const uint8_t* server_certificate_data,
                                      uint32_t server_certificate_data_size) override;

    void CreateSessionAndGenerateRequest(uint32_t promise_id,
                                                 SessionType session_type,
                                                 InitDataType init_data_type,
                                                 const uint8_t* init_data,
                                                 uint32_t init_data_size) override;

    void LoadSession(uint32_t promise_id,
                             SessionType session_type,
                             const char* session_id,
                             uint32_t session_id_size) override;

    void UpdateSession(uint32_t promise_id,
                               const char* session_id,
                               uint32_t session_id_size,
                               const uint8_t* response,
                               uint32_t response_size) override;

    void CloseSession(uint32_t promise_id,
                              const char* session_id,
                              uint32_t session_id_size) override;

    void RemoveSession(uint32_t promise_id,
                               const char* session_id,
                               uint32_t session_id_size) override;

    void TimerExpired(void* context) override;

    Status Decrypt(const InputBuffer& encrypted_buffer,
                           DecryptedBlock* decrypted_buffer) override;

    Status InitializeAudioDecoder(
            const AudioDecoderConfig& audio_decoder_config) override;

    Status InitializeVideoDecoder(
            const VideoDecoderConfig& video_decoder_config) override;

    void DeinitializeDecoder(StreamType decoder_type) override;

    void ResetDecoder(StreamType decoder_type) override;

    Status DecryptAndDecodeFrame(const InputBuffer& encrypted_buffer,
                                         VideoFrame* video_frame) override;

    Status DecryptAndDecodeSamples(const InputBuffer& encrypted_buffer,
                                           AudioFrames* audio_frames) override;

    void OnPlatformChallengeResponse(
            const PlatformChallengeResponse& response) override;

    void OnQueryOutputProtectionStatus(
            QueryResult result,
            uint32_t link_mask,
            uint32_t output_protection_mask) override;

    void OnStorageId(uint32_t version,
                             const uint8_t* storage_id,
                             uint32_t storage_id_size) override;

    void Destroy() override;


};

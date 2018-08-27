#pragma once

#include <cstdio>
#include "extern/cdmapi.h"
using namespace cdm;

class CDMProxy_8 : ContentDecryptionModule_8 {
private:
    ContentDecryptionModule_8 *orig_cdm;
    FILE *dumpfile;
    FILE *videodump;
    DecryptedBlock *temp_block;

public:
    explicit CDMProxy_8(ContentDecryptionModule_8 *passed_cdm);
    ~CDMProxy_8() override = default;


    void Initialize(bool allow_distinctive_identifier,
                            bool allow_persistent_state) override;

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

    void Destroy() override;


};

class DecryptedProxyBlock : public DecryptedBlock {
public:
    void SetDecryptedBuffer(Buffer* buffer) override;
    Buffer* DecryptedBuffer() override;

    void SetTimestamp(int64_t timestamp) override;
    int64_t Timestamp() const override;

    DecryptedProxyBlock() = default;

    ~DecryptedProxyBlock() override = default;

private:
    int64_t ts = 0;
    Buffer *buf = nullptr;
};
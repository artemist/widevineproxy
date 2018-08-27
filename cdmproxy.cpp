#include "cdmproxy.h"
#include "printing.h"
#include <iostream>

CDMProxy_8::CDMProxy_8(ContentDecryptionModule_8 *passed_cdm) : ContentDecryptionModule_8() {
    orig_cdm = passed_cdm;
    dumpfile = fopen("/tmp/dumpfile", "wb");
    videodump = fopen("/tmp/videodump", "wb");
    temp_block = new DecryptedProxyBlock();
}

void CDMProxy_8::Initialize(bool allow_distinctive_identifier,
                        bool allow_persistent_state) {
#ifdef DEBUG
    std::cerr << "Initializing CDM " << with_str(allow_distinctive_identifier) << " distinctive identifiers and " << \
        with_str(allow_persistent_state) << " persistent state" << std::endl;

    fprintf(stderr, "%zx\n", (size_t)orig_cdm);
#endif

    fflush(stderr);
    dump_memory((void*)orig_cdm, 80);

    orig_cdm->Initialize(allow_distinctive_identifier, allow_persistent_state);
    std::cerr << "Init returned" << std::endl;
}

void CDMProxy_8::SetServerCertificate(uint32_t promise_id, const uint8_t *server_certificate_data,
                                      uint32_t server_certificate_data_size) {
#ifdef DEBUG
    std::cerr << "Setting certificate from promise id " << promise_id << std::endl;
#endif
    orig_cdm->SetServerCertificate(promise_id, server_certificate_data, server_certificate_data_size);

}

void
CDMProxy_8::CreateSessionAndGenerateRequest(uint32_t promise_id, SessionType session_type, InitDataType init_data_type,
                                            const uint8_t *init_data, uint32_t init_data_size) {
#ifdef DEBUG
    std::cerr << "Creating session for promise " << promise_id << " of type " << session_type_str(session_type) << std::endl;
#endif
    orig_cdm->CreateSessionAndGenerateRequest(promise_id, session_type, init_data_type, init_data, init_data_size);

}

void CDMProxy_8::LoadSession(uint32_t promise_id, SessionType session_type, const char *session_id,
                             uint32_t session_id_size) {
#ifdef DEBUG
    std::cerr << "LoadSession" << std::endl;
#endif
    orig_cdm->LoadSession(promise_id, session_type, session_id, session_id_size);
}

void CDMProxy_8::UpdateSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size,
                               const uint8_t *response, uint32_t response_size) {
    std::cerr << "UpdateSession" << std::endl;
    orig_cdm->UpdateSession(promise_id, session_id, session_id_size, response, response_size);
}

void CDMProxy_8::CloseSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size) {
    std::cerr << "CloseSession" << std::endl;
    orig_cdm->CloseSession(promise_id, session_id, session_id_size);
}

void CDMProxy_8::RemoveSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size) {
    std::cerr << "RemoveSession" << std::endl;
    orig_cdm->RemoveSession(promise_id, session_id, session_id_size);
}

void CDMProxy_8::TimerExpired(void *context) {
    std::cerr << "TimerExpired" << std::endl;
    orig_cdm->TimerExpired(context);
}

Status CDMProxy_8::Decrypt(const InputBuffer &encrypted_buffer, DecryptedBlock *decrypted_buffer) {
    auto result = orig_cdm->Decrypt(encrypted_buffer, decrypted_buffer);

    auto buffer = decrypted_buffer->DecryptedBuffer();
    auto raw_buf = buffer->Data();
    auto buf_size = buffer->Size();
    fwrite(raw_buf, 1, buf_size, dumpfile);

    return result;

}

Status CDMProxy_8::InitializeAudioDecoder(const AudioDecoderConfig &audio_decoder_config) {
    std::cerr << "InitializeAudioDecoder" << std::endl;
    return orig_cdm->InitializeAudioDecoder(audio_decoder_config);
}

Status CDMProxy_8::InitializeVideoDecoder(const VideoDecoderConfig &video_decoder_config) {
    std::cerr << "InitializeVideoDecoder" << std::endl;
    return orig_cdm->InitializeVideoDecoder(video_decoder_config);
}

void CDMProxy_8::DeinitializeDecoder(StreamType decoder_type) {
    std::cerr << "DeinitilizeDecoder" << std::endl;
    orig_cdm->DeinitializeDecoder(decoder_type);
}

void CDMProxy_8::ResetDecoder(StreamType decoder_type) {
    std::cerr << "ResetDecoder" << std::endl;
    orig_cdm->ResetDecoder(decoder_type);
}

Status CDMProxy_8::DecryptAndDecodeFrame(const InputBuffer &encrypted_buffer, VideoFrame *video_frame) {
    std::cerr << "DecryptAndDecodeFrame" << std::endl;
#ifdef SHADY
    orig_cdm->Decrypt(encrypted_buffer, temp_block);
    auto buffer = temp_block->DecryptedBuffer();
    auto raw_buf = buffer->Data();
    auto buf_size = buffer->Size();
    fwrite(raw_buf, 1, buf_size, videodump);
#endif



    return orig_cdm->DecryptAndDecodeFrame(encrypted_buffer, video_frame);
}

/// Decrypt and decode audio data. I haven't seen anything use it in Firefox yet.
/// \param encrypted_buffer encrypted data
/// \param audio_frames decrypted audio data
/// \return did it work?
Status CDMProxy_8::DecryptAndDecodeSamples(const InputBuffer &encrypted_buffer, AudioFrames *audio_frames) {
    std::cerr << "DecryptAndDecodeSamples" << std::endl;
    return orig_cdm->DecryptAndDecodeSamples(encrypted_buffer, audio_frames);
}

void CDMProxy_8::OnPlatformChallengeResponse(const PlatformChallengeResponse &response) {
    std::cerr << "OnPlatformChallengeResponse" << std::endl;
    orig_cdm->OnPlatformChallengeResponse(response);
}

void
CDMProxy_8::OnQueryOutputProtectionStatus(QueryResult result, uint32_t link_mask, uint32_t output_protection_mask) {
    std::cerr << "OnQueryOutputProtectionStatus" << std::endl;
    orig_cdm->OnQueryOutputProtectionStatus(result, link_mask, output_protection_mask);
}

void CDMProxy_8::Destroy() {
    std::cerr << "Destroy" << std::endl;
    orig_cdm->Destroy();
    fflush(dumpfile);
    fflush(videodump);
}

void DecryptedProxyBlock::SetDecryptedBuffer(Buffer *buffer) {
    buf = buffer;
}

Buffer *DecryptedProxyBlock::DecryptedBuffer() {
    return buf;
}

void DecryptedProxyBlock::SetTimestamp(int64_t timestamp) {
    ts = timestamp;
}

int64_t DecryptedProxyBlock::Timestamp() const {
    return ts;
}
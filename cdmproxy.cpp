#include "cdmproxy.h"
#include "printing.h"
#include <iostream>

CDMProxy_9::CDMProxy_9(ContentDecryptionModule_9 *passed_cdm) : ContentDecryptionModule_9() {
    orig_cdm = passed_cdm;
}

void CDMProxy_9::Initialize(bool allow_distinctive_identifier,
                        bool allow_persistent_state) {
    std::cerr << "Initializing CDM " << with_str(allow_distinctive_identifier) << " distinctive identifiers and " << \
        with_str(allow_persistent_state) << " Persistent state" << std::endl;
    orig_cdm->Initialize(allow_distinctive_identifier, allow_persistent_state);
}

void CDMProxy_9::SetServerCertificate(uint32_t promise_id, const uint8_t *server_certificate_data,
                                      uint32_t server_certificate_data_size) {
    std::cerr << "Setting certificate from promise id " << promise_id << std::endl;
    orig_cdm->SetServerCertificate(promise_id, server_certificate_data, server_certificate_data_size);

}

void
CDMProxy_9::CreateSessionAndGenerateRequest(uint32_t promise_id, SessionType session_type, InitDataType init_data_type,
                                            const uint8_t *init_data, uint32_t init_data_size) {
    std::cerr << "Creating session for promise " << promise_id << " of type " << session_type_str(session_type) << std::endl;
    orig_cdm->CreateSessionAndGenerateRequest(promise_id, session_type, init_data_type, init_data, init_data_size);

}

void CDMProxy_9::LoadSession(uint32_t promise_id, SessionType session_type, const char *session_id,
                             uint32_t session_id_size) {
    orig_cdm->LoadSession(promise_id, session_type, session_id, session_id_size);
}

void CDMProxy_9::UpdateSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size,
                               const uint8_t *response, uint32_t response_size) {
    orig_cdm->UpdateSession(promise_id, session_id, session_id_size, response, response_size);
}

void CDMProxy_9::CloseSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size) {
    orig_cdm->CloseSession(promise_id, session_id, session_id_size);
}

void CDMProxy_9::RemoveSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size) {
    orig_cdm->RemoveSession(promise_id, session_id, session_id_size);
}

void CDMProxy_9::TimerExpired(void *context) {
    orig_cdm->TimerExpired(context);
}

Status CDMProxy_9::Decrypt(const InputBuffer &encrypted_buffer, DecryptedBlock *decrypted_buffer) {
    return orig_cdm->Decrypt(encrypted_buffer, decrypted_buffer);
}

Status CDMProxy_9::InitializeAudioDecoder(const AudioDecoderConfig &audio_decoder_config) {
    return orig_cdm->InitializeAudioDecoder(audio_decoder_config);
}

Status CDMProxy_9::InitializeVideoDecoder(const VideoDecoderConfig &video_decoder_config) {
    return orig_cdm->InitializeVideoDecoder(video_decoder_config);
}

void CDMProxy_9::DeinitializeDecoder(StreamType decoder_type) {
    orig_cdm->DeinitializeDecoder(decoder_type);
}

void CDMProxy_9::ResetDecoder(StreamType decoder_type) {
    orig_cdm->ResetDecoder(decoder_type);
}

Status CDMProxy_9::DecryptAndDecodeFrame(const InputBuffer &encrypted_buffer, VideoFrame *video_frame) {
    return orig_cdm->DecryptAndDecodeFrame(encrypted_buffer, video_frame);
}

Status CDMProxy_9::DecryptAndDecodeSamples(const InputBuffer &encrypted_buffer, AudioFrames *audio_frames) {
    return orig_cdm->DecryptAndDecodeSamples(encrypted_buffer, audio_frames);
}

void CDMProxy_9::OnPlatformChallengeResponse(const PlatformChallengeResponse &response) {
    orig_cdm->OnPlatformChallengeResponse(response);
}

void
CDMProxy_9::OnQueryOutputProtectionStatus(QueryResult result, uint32_t link_mask, uint32_t output_protection_mask) {
    orig_cdm->OnQueryOutputProtectionStatus(result, link_mask, output_protection_mask);
}

void CDMProxy_9::Destroy() {
    orig_cdm->Destroy();
}

void CDMProxy_9::OnStorageId(uint32_t version, const uint8_t *storage_id, uint32_t storage_id_size) {
    orig_cdm->OnStorageId(version, storage_id, storage_id_size);
}

void CDMProxy_9::GetStatusForPolicy(uint32_t promise_id, const Policy &policy) {
    orig_cdm->GetStatusForPolicy(promise_id, policy);
}

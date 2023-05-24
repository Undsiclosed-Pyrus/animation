#pragma once

#include "mf_desfire.h"
#include <lib/nfc/protocols/nfca/nfca_poller.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MfDesfirePoller MfDesfirePoller;

typedef enum {
    MfDesfirePollerEventTypeReadSuccess,
    MfDesfirePollerEventTypeReadFailed,
} MfDesfirePollerEventType;

typedef struct {
    union {
        MfDesfireError error;
    };
} MfDesfirePollerEventData;

typedef struct {
    MfDesfirePollerEventType type;
    MfDesfirePollerEventData* data;
} MfDesfirePollerEvent;

typedef enum {
    MfDesfirePollerCommandContinue = NfcaPollerCommandContinue,
    MfDesfirePollerCommandReset = NfcaPollerCommandReset,
    MfDesfirePollerCommandStop = NfcaPollerCommandStop,
} MfDesfirePollerCommand;

typedef MfDesfirePollerCommand (
    *MfDesfirePollerCallback)(MfDesfirePollerEvent event, void* context);

MfDesfirePoller* mf_desfire_poller_alloc(NfcaPoller* nfca_poller);

void mf_desfire_poller_free(MfDesfirePoller* instance);

MfDesfireError mf_desfire_poller_start(
    MfDesfirePoller* instance,
    NfcaPollerEventCallback callback,
    void* context);

MfDesfireError mf_desfire_poller_read(
    MfDesfirePoller* instance,
    MfDesfirePollerCallback callback,
    void* context);

MfDesfireError mf_desfire_poller_get_data(MfDesfirePoller* instance, MfDesfireData* data);

MfDesfireError mf_desfire_poller_stop(MfDesfirePoller* instance);

#ifdef __cplusplus
}
#endif
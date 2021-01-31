#include <windows.h>
#include <wincrypt.h>
#include "qc/random.h"
#include "qc/error.h"

qc_result qc_rnd_init(qc_rnd* state, qc_err* err) {
    qc_result ret = QC_SUCCESS;
    HCRYPTPROV hCryptProv;
    if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0) == 0) {
        qc_err_set(err, "Failed to acquire WIN32 cryptographic context");
        ret = QC_FAILURE;
        goto exit;
    }
    if (CryptGenRandom(hCryptProv, sizeof(uint64_t), (PBYTE) &state->s64) == 0) {
        qc_err_set(err, "Failed to acquire entropy from WIN32 cryptographic context");
        ret = QC_FAILURE;
        // should release context anyway so we don't jump to exit yet
    }
    if (CryptReleaseContext(hCryptProv, 0) == 0) {
        qc_err_set(err,
                   "Failed to release WIN32 cryptographic context "
                   "(this should never happen, report bug immediately!)");
        ret = QC_FAILURE;
        goto exit;
    }
exit:
    if (ret == QC_FAILURE) {
        state->s64 = 0;
    }
    return ret;
}

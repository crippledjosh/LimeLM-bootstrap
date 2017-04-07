#include "TurboActivate.h"

#include <stdio.h>
#include <stdlib.h>

// Support Unicode compilation and non-Windows compilation
#ifdef _WIN32
#include <tchar.h>
#else
#define _T(x) x
typedef char    TCHAR;
#endif

// To use the static version of TurboActivate then uncomment the next line
//#define TURBOACTIVATE_STATIC

// Include the correct library on Windows
#ifdef TURBOACTIVATE_STATIC
#ifdef _DEBUG
#ifdef _DLL
#pragma comment(lib, "TurboActivate-MDd.lib")
#else
#pragma comment(lib, "TurboActivate-MTd.lib")
#endif
#else
#ifdef _DLL
#pragma comment(lib, "TurboActivate-MD.lib")
#else
#pragma comment(lib, "TurboActivate-MT.lib")
#endif
#endif
#else
#pragma comment (lib, "TurboActivate.lib")
#endif




/* The handle used for TurboActivate function calls. */
uint32_t taHandle;
uint32_t trialFlags;

int setupHandleAndFlags(char* path){
    TA_PDetsFromPath(path);
    
    trialFlags = TA_VERIFIED_TRIAL | TA_SYSTEM;
    taHandle = TA_GetHandle(_T("1c2b92be58d39c417a8b79.76830740"));
    return taHandle == 0;
}

int isGenuineEx(){
    /* Used to store TurboActivate responses. */
    GENUINE_OPTIONS opts = {0};
    opts.nLength = sizeof(GENUINE_OPTIONS);
    
    // In this example we won't show an error if the activation
    // was done offline by passing the TA_SKIP_OFFLINE flag
    opts.flags = TA_SKIP_OFFLINE;
    
    // How often to verify with the LimeLM servers (90 days)
    opts.nDaysBetweenChecks = 90;
    
    // The grace period if TurboActivate couldn't connect to the servers.
    // after the grace period is over TA_IsGenuineEx() will return TA_FAIL instead of
    // TA_E_INET or TA_E_INET_DELAYED
    opts.nGraceDaysOnInetErr = 14;
    return TA_IsGenuineEx(taHandle, &opts);
    
}

int isGenuine(){
    return TA_IsGenuine(taHandle);
}

int activate(){
    return TA_Activate(taHandle, NULL);
}

int isActivated(){
    return TA_IsActivated(taHandle);
}

int trailDaysRemaining(){
    uint32_t trialDays = 0;
    TA_TrialDaysRemaining(taHandle, trialFlags, &trialDays);
    return trialDays;
}

int useTrial(){
    return TA_UseTrial(taHandle, trialFlags, NULL);
}

int checkAndSaveKey(char* key){
    STRCTYPE pKey = _T(key);
    return TA_CheckAndSavePKey(taHandle, pKey, TA_USER);
}

int deactivate(char eraseKey){
    return TA_Deactivate(taHandle, eraseKey);
}

STRTYPE getKey(){
    int size = TA_GetPKey(taHandle, 0, 0);
    STRTYPE key = (char *) malloc(size);
    TA_GetPKey(taHandle, key, size);
    return key;
}

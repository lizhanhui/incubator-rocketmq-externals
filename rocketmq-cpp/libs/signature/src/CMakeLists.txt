include_directories(${PROJECT_SOURCE_DIR}/libs/signature/include)
SET(SIGNATURE_SOURCE_FILES
        base64.c
        hmac.c
        param_list.c
        sha1.c
        sha256.c
        sha512.c
        spas_client.c)
ADD_LIBRARY(signature SHARED ${SIGNATURE_SOURCE_FILES})
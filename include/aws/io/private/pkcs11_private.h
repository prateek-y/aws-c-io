#ifndef AWS_IO_PKCS11_PRIVATE_H
#define AWS_IO_PKCS11_PRIVATE_H

/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#include <aws/io/pkcs11.h>

struct aws_string;

/**
 * pkcs11_private.h
 * This file declares symbols that are private to aws-c-io but need to be
 * accessed from multiple .c files.
 */

/* aws_pkcs11_t: equivalent to CK_SLOT_ID / CK_SESSION_HANDLE / CK_OBJECT_HANDLE.
 * including PKCS#11 headers is weird, so outside of pkcs11.c we'll just use this typedef instead */
typedef unsigned long aws_pkcs11_t;

AWS_EXTERN_C_BEGIN

/**
 * Find the slot that meets all criteria:
 * - has a token
 * - if match_slot_id is non-null, then slot IDs must match
 * - if match_token_label is non-null, then labels must match
 * The function fails unless it finds exactly one slot meeting all criteria.
 */
AWS_IO_API
int aws_pkcs11_lib_find_slot_with_token(
    struct aws_pkcs11_lib *pkcs11_lib,
    const aws_pkcs11_t *match_slot_id,
    const struct aws_string *match_token_label,
    aws_pkcs11_t *out_slot_id);

AWS_IO_API
int aws_pkcs11_lib_open_session(
    struct aws_pkcs11_lib *pkcs11_lib,
    aws_pkcs11_t slot_id,
    aws_pkcs11_t *out_session_handle);

AWS_IO_API
void aws_pkcs11_lib_close_session(struct aws_pkcs11_lib *pkcs11_lib, aws_pkcs11_t session_handle);

AWS_IO_API
int aws_pkcs11_lib_login_user(
    struct aws_pkcs11_lib *pkcs11_lib,
    aws_pkcs11_t session_handle,
    const struct aws_string *optional_user_pin);

/**
 * Find the object that meets all criteria:
 * - is private key
 * - if match_label is non-null, then labels must match
 * The function fails unless it finds exactly one object meeting all criteria.
 */
AWS_IO_API
int aws_pkcs11_lib_find_private_key(
    struct aws_pkcs11_lib *pkcs11_lib,
    aws_pkcs11_t session_handle,
    const struct aws_string *match_label,
    aws_pkcs11_t *out_key_object_handle);

AWS_EXTERN_C_END
#endif /* AWS_IO_PKCS11_PRIVATE_H */

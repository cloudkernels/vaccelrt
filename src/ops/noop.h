/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "include/ops/noop.h"

struct vaccel_session;
struct vaccel_arg;

int vaccel_noop_unpack(struct vaccel_session *sess, struct vaccel_arg *read,
		       int nr_read, struct vaccel_arg *write, int nr_write);

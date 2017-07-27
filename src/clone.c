/*
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <git2.h>
#include <stdlib.h>
#include <string.h>

typedef void (*js_callback) (double, double, double);

int cancel = 0;

static int
transfer_cb (const git_transfer_progress *stats, void *callback) {
  double total = (double) stats->total_objects;
  double received = (double) stats->received_objects;
  double received_bytes = (double) stats->received_bytes;
  if (callback)
    ((js_callback) callback)(received, total, received_bytes);
  return cancel;
}

void webgit_clone_cancel () {
  cancel = -1;
}

static char *
get_repo_basename (char *uri) {
  char *start, *end, *basename;

  for (end = uri + strlen(uri) - 1, start = end; *start != '/'; start--);
  char *test = "tig.";  /* ".git" backwards */
  size_t len = end - start;
  size_t j = len;
  for (int i = 0; i < 3; end--, test++, j--, i++) {
    if (*end != *test) goto NO_DOT_GIT;
  }
  len = --j;

  NO_DOT_GIT:
  basename = malloc(len + 1);
  memcpy(basename, ++start, len);
  basename[len] = 0;

  return basename;
}

git_repository *
webgit_clone (char *uri, char *dest, char *branch, js_callback cb) {
  git_repository *repo = NULL;
  git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
  cancel = 0;

  opts.checkout_branch = branch;
  opts.fetch_opts.callbacks.transfer_progress = transfer_cb;
  opts.fetch_opts.callbacks.payload = cb;

  if (!dest) dest = get_repo_basename(uri);

  if (git_clone(&repo, uri, dest, &opts) < 0)
    repo = NULL;

  return repo;
}

#ifdef _TEST_BASENAME

#include <stdio.h>

int main (int argc, char **argv) {
  if (!strcmp(argv[1], "basename")) {
    printf("%s\n", get_repo_basename(argv[2]));
  }
}

#endif

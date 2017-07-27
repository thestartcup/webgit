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

git_repository * webgit_init (char *path) {
  git_repository *repo = NULL;

  git_libgit2_init();
  int err = git_repository_init(&repo, path, 0);

  if (err) repo = NULL;

  git_libgit2_shutdown();
  free(path);
  return repo;
}

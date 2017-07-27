###
# Copyright © 2017 The Start Cup, LLC. All rights reserved.
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
###

fs = require 'fs'

class GitRepository
  constructor: (@ptr) ->


@git =
  clone: (uri, dest, branch, callback) ->
    uri_ = Pointer_stringify uri
    dest_ = if dest? then Pointer_stringify dest else 0
    branch_ = if branch? then Pointer_stringify branch else 0
    callback_ = if callback? then Runtime.addFunction callback else 0
    new GitRepository bindings.clone uri_, dest_, branch_, callback_

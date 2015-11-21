<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\stream;

use hhpack\process\OutputResult;

interface StreamManager
{
    public function read() : void;
    public function close() : void;
    public function getOutputResult() : OutputResult;
}

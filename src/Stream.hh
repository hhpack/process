<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process;

interface Stream
{
    public function ready() : bool;
    public function notReady() : bool;
    public function isOpened() : bool;
    public function isClosed() : bool;
    public function close() : void;
}

<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\output;

use hhpack\process\Writable;

final class Stderr implements WritableStream
{

    public function isOpened() : bool
    {
        return is_resource(STDERR);
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function ready() : bool
    {
        return $this->isOpened();
    }

    public function notReady() : bool
    {
        return $this->ready() === false;
    }

    public function close() : void
    {
    }

    public function write(string $output) : int
    {
        fputs(STDERR, $output);
        return strlen($output);
    }

}
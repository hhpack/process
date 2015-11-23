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

final class Stdout implements WritableStream
{

    private bool $opened = true;

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function close() : void
    {
        $this->opened = false;
    }

    public function write(string $output) : int
    {
        fputs(STDOUT, $output);
        return strlen($output);
    }

}

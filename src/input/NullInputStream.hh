<?hh //strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\input;

use hhpack\process\Writable;

final class NullInputStream implements ReadableStream<int>
{

    private bool $opened = true;

    public function eof() : bool
    {
        return true;
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function read(int $length) : string
    {
        return '';
    }

    public function pipeTo(Writable<int> $output) : void
    {
    }

    public function close() : void
    {
        $this->opened = false;
    }

}

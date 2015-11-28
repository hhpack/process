<?hh // strict

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
use hhpack\process\output\BufferedOutputStream;

final class StringInputStream implements ReadableStream<int>
{

    private bool $opened = true;

    public function __construct(
        private string $input
    )
    {
    }

    public function eof() : bool
    {
        return strlen($this->input) <= 0;
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function read(int $length = 4096) : string
    {
        $input = $this->input;
        $this->input = '';

        return $input;
    }

    public function close() : void
    {
        $this->opened = false;
    }

}

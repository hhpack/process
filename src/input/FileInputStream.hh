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

final class FileInputStream implements ReadableStream<int>
{

    private ResourceInputStream $stream;

    public function __construct(
        private string $path
    )
    {
        $handle = fopen($this->path, 'r');
        $this->stream = new ResourceInputStream($handle);
    }

    public function eof() : bool
    {
        return $this->stream->eof();
    }

    public function isOpened() : bool
    {
        return $this->stream->isOpened();
    }

    public function isClosed() : bool
    {
        return $this->stream->isClosed();
    }

    public function ready() : bool
    {
        return $this->stream->ready();
    }

    public function notReady() : bool
    {
        return $this->stream->notReady();
    }

    public function read(int $length = 4096) : string
    {
        return $this->stream->read($length);
    }

    public function close() : void
    {
        $this->stream->close();
    }

}

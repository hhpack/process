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

use hhpack\process\StreamType;

final class OutputPipeStream implements WritableStream
{

    private bool $opened = true;

    public function __construct(
        private StreamType $type,
        private resource $handle
    )
    {
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function write(string $output) : int
    {
        return (int) fwrite($this->handle, $output);
    }

    public function close() : void
    {
        fclose($this->handle);
        $this->opened = false;
    }

}

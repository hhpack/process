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

    private int $position = 0;
    private bool $opened = true;

    public function __construct(
        private string $input = '',
        private Writable<int> $output = new BufferedOutputStream()
    )
    {
    }

    public function eof() : bool
    {
        return strlen($this->input) <= $this->position;
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function read(int $length) : void
    {
        $chunk = $this->consume($length);

        if ($chunk === '') {
            $this->close();
            return;
        }

        do {
            $failed = $this->output->write($chunk) <= 0;
        } while ($failed);
    }

    public function getOutput() : Writable<int>
    {
        return $this->output;
    }

    public function pipeTo(Writable<int> $output) : void
    {
        $this->output = $output;
    }

    public function close() : void
    {
        $this->opened = false;
    }

    private function consume(int $length) : string
    {
        // It will be typecast to string If the return value is FALSE
        $chunk = (string) substr($this->input, $this->position, $length);
        $chunkLength = strlen($chunk);

        $this->position += $chunkLength;

        return $chunk;
    }

}

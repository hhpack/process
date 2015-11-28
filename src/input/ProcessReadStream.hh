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
use hhpack\process\stream\StreamType;

final class ProcessReadStream implements ReadableStream<int>
{

    public function __construct(
        private StreamType $type,
        private resource $handle,
        private Writable<int> $output = new BufferedOutputStream()
    )
    {
        stream_set_blocking($this->handle, 0);
    }

    public function eof() : bool
    {
        return feof($this->handle);
    }

    public function isOpened() : bool
    {
        return is_resource($this->handle);
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function read(int $length = 4096) : void
    {
        $chunk = (string) fread($this->handle, $length);

        if ($chunk === '') {
            return;
        }

        $this->output->write($chunk);
    }

    public function getOutput() : Writable<int>
    {
        return $this->output;
    }

    public function pipeTo(Writable<int> $output) : void
    {
        $this->output = $output;
    }

    public function isStdout() : bool
    {
        return $this->type === StreamType::Stdout;
    }

    public function isStderr() : bool
    {
        return $this->type === StreamType::Stderr;
    }

    public function close() : void
    {
        fclose($this->handle);
    }

}

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

use hhpack\process\input\NullInputStream;
use hhpack\process\input\StringInputStream;
use hhpack\process\input\ReadableStream;
use hhpack\process\output\BufferedOutputStream;
use hhpack\process\stream\StreamType;

final class ProcessWriteStream implements WritableStream
{

    private BufferedOutputStream $bufferedOutput;
    private bool $opened = true;

    public function __construct(
        private StreamType $type,
        private resource $handle,
        private ReadableStream<int> $input = new NullInputStream()
    )
    {
        $this->bufferedOutput = new BufferedOutputStream();
        $this->input->pipeTo($this->bufferedOutput);
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function flush() : void
    {
        $this->readAll();
        $this->writeAll();
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

    private function readAll() : void
    {
        while ($this->input->eof() === false) {
            $this->input->read(4096);
        }
    }

    private function writeAll() : void
    {
        $stream = new StringInputStream((string) $this->bufferedOutput, $this);

        while ($stream->eof() === false) {
            $stream->read(1024 * 512); //512KB
        }

        $this->bufferedOutput->clear();
    }

}

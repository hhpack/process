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

    private ResourceOutputStream $stream; 
    private string $bufferedInput = '';

    public function __construct(
        private StreamType $type,
        resource $handle,
        private ReadableStream<int> $input = new NullInputStream()
    )
    {
        $this->stream = new ResourceOutputStream($handle);
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

    public function flush() : void
    {
        $this->readAll();
        $this->writeAll();
    }

    public function write(string $output) : int
    {
        return $this->stream->write($output);
    }

    public function close() : void
    {
        $this->stream->close();
    }

    private function readAll() : void
    {
        if ($this->input->isClosed()) {
            return;
        }

        $chunk = $this->input->read();

        if ($this->input->eof()) {
            $this->input->close();
        }

        $this->bufferedInput .= $chunk;
    }

    private function writeAll() : void
    {
        if ($this->isClosed() || $this->notReady()) {
            return;
        }

        while (strlen($this->bufferedInput) > 0) {
            $chunk = substr($this->bufferedInput, 0, 512);
            $writedBytes = $this->write($chunk);

            if ($writedBytes <= 0) {
                break;
            }
            $this->bufferedInput = substr($this->bufferedInput, $writedBytes);
        }

        if (strlen($this->bufferedInput) > 0
            || $this->input->isOpened()) {
            return;
        }

        $this->close();
    }

}

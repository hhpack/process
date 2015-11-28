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

    private string $bufferedInput = '';

    public function __construct(
        private StreamType $type,
        private resource $handle,
        private ReadableStream<int> $input = new NullInputStream()
    )
    {
        stream_set_blocking($this->handle, 0);
    }

    public function isOpened() : bool
    {
        return is_resource($this->handle);
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
    }

    private function readAll() : void
    {
        $bufferedInput = new BufferedOutputStream();
        $this->input->pipeTo($bufferedInput);

        while ($this->input->eof() === false) {
            $this->input->read();
        }

        $this->bufferedInput .= (string) $bufferedInput;
    }

    private function writeAll() : void
    {
        while (strlen($this->bufferedInput) > 0) {
            $chunk = substr($this->bufferedInput, 0, 512);
            $writedBytes = $this->write($chunk);

            if ($writedBytes <= 0) {
                break;
            }
            $this->bufferedInput = substr($this->bufferedInput, $writedBytes);
        }

        if (strlen($this->bufferedInput) > 0 || $this->input->isOpened()) {
            return;
        }

        $this->close();
    }

}

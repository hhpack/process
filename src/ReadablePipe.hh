<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process;

use RuntimeException;

final class ReadablePipe implements ReadableStream
{

    private bool $opened = true;
    private BufferedOutput $bufferedOutput;

    public function __construct(
        private resource $handle
    )
    {
        $this->bufferedOutput = new BufferedOutput();
    }

    public function eof() : bool
    {
        return feof($this->handle);
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
        $chunk = fread($this->handle, $length);
        $this->bufferedOutput->append($chunk);
    }

    public function getOutput() : BufferedOutput
    {
        return $this->bufferedOutput;
    }

    public function close() : void
    {
        fclose($this->handle);
        $this->opened = false;
    }

    public static function nullPipe() : ReadablePipe
    {
        $handle = fopen('/dev/null', 'r');

        if (is_resource($handle) === false) {
            throw new RuntimeException();
        }
        return new ReadablePipe($handle);
    }

}

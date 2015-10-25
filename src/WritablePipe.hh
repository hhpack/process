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

final class WritablePipe implements WritableStream
{

    private bool $opened = true;

    public function __construct(
        private PipeType $type,
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

    public static function nullPipe(PipeType $type) : WritablePipe
    {
        $handle = fopen('/dev/null', 'r');

        if (is_resource($handle) === false) {
            throw new RuntimeException();
        }

        return new WritablePipe($type, $handle);
    }

}

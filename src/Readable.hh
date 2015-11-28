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

interface Readable
{
    /**
     * Tests for end-of-file on a pointer
     */
    public function eof() : bool;

    /**
     * Read only bytes specified from the stream
     */
    public function read(int $length = 4096) : string;
}

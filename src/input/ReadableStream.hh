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

use hhpack\process\Stream;
use hhpack\process\Readable;
use hhpack\process\Writable;

// FIXME Remove getOutput() method
interface ReadableStream<T> extends Stream, Readable
{
    public function getOutput() : Writable<T>;
    public function pipeTo(Writable<T> $output) : void;
}

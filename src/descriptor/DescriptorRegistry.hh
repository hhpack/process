<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\descriptor;

use hhpack\process\StreamType;
use hhpack\process\StreamManager;
use hhpack\process\stream\StreamRegistry;
use hhpack\process\DescriptorSpecification;
use hhpack\process\input\InputPipeStream;
use hhpack\process\output\OutputPipeStream;

interface DescriptorRegistry
{
    public function createPipeManager(array<int, resource> $streamHandles) : StreamManager;
    public function toArray() : array<int, array<string>>;
}

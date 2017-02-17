<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Descriptor;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Stream\StreamManager;
use HHPack\Process\Stream\StreamRegistry;
use HHPack\Process\DescriptorSpecification;
use HHPack\Process\Input\InputPipeStream;
use HHPack\Process\Output\OutputPipeStream;

interface DescriptorRegistry
{
    public function createStreamManager(array<int, resource> $streamHandles) : StreamManager;
    public function toArray() : array<int, array<string>>;
}

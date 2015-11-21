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

interface DescriptorSpecification
{
    public function getStreamType() : StreamType;
    public function getStreamValues() : array<string>;
    public function isReadDescriptor() : bool;
    public function isWriteDescriptor() : bool;
}

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

final class FileDescriptorRegistry
{

    public function __construct(
        private ImmMap<PipeType, DescriptorSpecification> $registry
    )
    {
    }

    public static function fromArray(Traversable<DescriptorSpecification> $descriptors) : FileDescriptorRegistry
    {
        $registry = Map {};

        foreach ($descriptors as $descriptor) {
            $registry->set($descriptor->getPipeType(), $descriptor);
        }

        return new FileDescriptorRegistry( $registry->toImmMap() );
    }

}

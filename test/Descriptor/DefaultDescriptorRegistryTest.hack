namespace HHPack\Process\Test;

use type HHPack\Process\Stream\StreamType;
use type HHPack\Process\Descriptor\{
  WriteDescriptor,
  ReadDescriptor,
  DefaultDescriptorRegistry,
};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class DefaultDescriptorRegistryTest extends HackTest {
  public function testToArray(): void {
    $registry = new DefaultDescriptorRegistry(
      new WriteDescriptor(StreamType::Stdin, ['pipe', 'r']),
      new ReadDescriptor(StreamType::Stdout, ['pipe', 'w']),
      new ReadDescriptor(StreamType::Stderr, ['pipe', 'w']),
    );
    $result = $registry->toDArray();

    expect($result[0][0])->toBeSame('pipe');
    expect($result[0][1])->toBeSame('r');

    expect($result[1][0])->toBeSame('pipe');
    expect($result[1][1])->toBeSame('w');

    expect($result[2][0])->toBeSame('pipe');
    expect($result[2][1])->toBeSame('w');
  }
}

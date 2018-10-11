<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\ReadDescriptor;
use LogicException;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class ReadDescriptorTest extends HackTest {
  public function testUnsupportType(): void {
    expect(() ==> {
      $descriptor = new ReadDescriptor(StreamType::Stdin, ['pipe', 'r']);
    })->toThrow(LogicException::class);
  }
}

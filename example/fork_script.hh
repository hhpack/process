<?hh // partial

foreach ($argv as $value) {
    $text = sprintf('%s%s', (string) $value, PHP_EOL);
    fwrite(STDOUT, $text);
}

exit(0);

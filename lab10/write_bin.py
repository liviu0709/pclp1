bytes: bytes = b'\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09'

with open('bytes.bin', 'wb') as f:
    f.write(bytes)



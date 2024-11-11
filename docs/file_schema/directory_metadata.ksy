meta:
  id: cataboard_directory_metadata
  file-extension: cdm
  endian: le
types:
  string:
    seq:
      - id: len
        type: u4
      - id: data
        type: strz
        encoding: UTF-8
        size: len
seq:
  - id: magic
    contents: "CTBDN"
  - id: version
    type: u4
  - id: name
    type: string
  - id: next_board_id
    type: u4
  - id: board_num
    type: u4
  - id: board_path
    type: string
    repeat: board_num
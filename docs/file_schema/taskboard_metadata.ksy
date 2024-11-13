meta:
  id: cataboard_taskboard_metadata
  file-extension: cbm
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
    contents: "CTBBN"
  - id: id
    type: u4
  - id: name
    type: string
  - id: task_num
    type: u4
  - id: task_id
    type: u4
    repeat: task_num
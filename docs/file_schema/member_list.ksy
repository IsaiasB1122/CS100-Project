meta:
  id: cataboard_member_list
  file-extension: cml
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
  member_entry:
    seq:
      - id: id
        type: u4
      - id: name
        type: string
seq:
  - id: magic
    contents: "CTML"
  - id: next_member_id
    type: u4
  - id: member_num
    type: u4
  - id: member
    type: u4
    repeat: member_entry
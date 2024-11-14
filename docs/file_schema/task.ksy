meta:
  id: cataboard_task
  file-extension: cte
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
  note_list:
    import: note_list.ksy
    # * not real syntax, treat this type as seq from note_list.ksy
seq:
  - id: magic
    contents: "CTT"
  - id: id
    type: u4
  - id: name
    type: string
  - id: category_id
    type: u4
  - id: assigned_member_num
    type: u4
  - id: assigned_member
    type: u4
    repeat: assigned_member_num
  - id: note_list
    type: note_list
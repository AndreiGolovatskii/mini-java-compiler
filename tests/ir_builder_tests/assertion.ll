; ModuleID = 'main'
source_filename = "main"

define void @"Assertion#simple"() {
Entry:
  %0 = and i1 true, true
  br i1 %0, label %Ok, label %Fail

Fail:                                             ; preds = %Entry
  call void @exit(i32 1)
  unreachable

Ok:                                               ; preds = %Entry
  %1 = icmp eq i32 1, 1
  br i1 %1, label %Ok2, label %Fail1

Fail1:                                            ; preds = %Ok
  call void @exit(i32 1)
  unreachable

Ok2:                                              ; preds = %Ok
  %2 = icmp eq i32 2, 2
  br i1 %2, label %Ok4, label %Fail3

Fail3:                                            ; preds = %Ok2
  call void @exit(i32 1)
  unreachable

Ok4:                                              ; preds = %Ok2
  %3 = icmp eq i32 256, 256
  br i1 %3, label %Ok6, label %Fail5

Fail5:                                            ; preds = %Ok4
  call void @exit(i32 1)
  unreachable

Ok6:                                              ; preds = %Ok4
  %4 = icmp eq i32 -1, -1
  br i1 %4, label %Ok8, label %Fail7

Fail7:                                            ; preds = %Ok6
  call void @exit(i32 1)
  unreachable

Ok8:                                              ; preds = %Ok6
  ret void
}

declare void @exit(i32)

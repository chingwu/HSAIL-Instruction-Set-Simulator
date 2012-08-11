#include "brig_control_block.h"
#include "brig_function.h"

namespace hsa {
namespace brig {

BrigControlBlock &BrigControlBlock::operator++() {
  dir_iterator E = S_.end();
  if(it_ == E) return *this;

  for(++it_; it_ != E; ++it_)
     if(isa<BrigDirectiveLabel>(it_)) return *this;

  return *this;
}

BrigControlBlock cb_begin(const BrigFunction &F) {
  return BrigControlBlock(F.S_, F.it_);
}

BrigControlBlock cb_end(const BrigFunction &F) {
  dir_iterator dirE(F.S_.directives + F.getMethod()->d_nextDirective);
  assert(!isa<BrigDirectiveLabel>(dirE) && "Label outside of function!?");
  BrigControlBlock E(F.S_, dirE);
  ++E;
  return E;
}

BrigControlBlock BrigFunction::begin() const { return cb_begin(*this); }
BrigControlBlock BrigFunction::end() const { return cb_end(*this); }

} // namespace brig
} // namespace hsa
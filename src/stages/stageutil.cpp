#include <cstdlib>
#include "seq/stageutil.h"

using namespace seq;

Nop& stageutil::nop()
{
	return Nop::make();
}

Copy& stageutil::copy()
{
	return Copy::make();
}

Filter& stageutil::filter(Func& func)
{
	return Filter::make(func);
}

OpStage& stageutil::op(std::string name, SeqOp op)
{
	return OpStage::make(std::move(name), op);
}

Hash& stageutil::hash(std::string name, SeqHash hash)
{
	return Hash::make(std::move(name), hash);
}

Print& stageutil::print()
{
	return Print::make();
}

RevComp& stageutil::revcomp()
{
	return RevComp::make();
}

Split& stageutil::split(Expr *k, Expr *step)
{
	return Split::make(k, step);
}

Split& stageutil::split(seq_int_t k, seq_int_t step)
{
	return Split::make(k, step);
}

Substr& stageutil::substr(Expr *start, Expr *len)
{
	return Substr::make(start, len);
}

Substr& stageutil::substr(seq_int_t start, seq_int_t len)
{
	return Substr::make(start, len);
}

Len& stageutil::len()
{
	return Len::make();
}

Count& stageutil::count()
{
	return Count::make();
}

Range& stageutil::range(Expr *from, Expr *to, Expr *step)
{
	return Range::make(from, to, step);
}

Range& stageutil::range(Expr *from, Expr *to)
{
	return Range::make(from, to);
}

Range& stageutil::range(Expr *to)
{
	return Range::make(to);
}

Range& stageutil::range(seq_int_t from, seq_int_t to, seq_int_t step)
{
	return Range::make(from, to, step);
}

Range& stageutil::range(seq_int_t from, seq_int_t to)
{
	return Range::make(from, to);
}

Range& stageutil::range(seq_int_t to)
{
	return Range::make(to);
}

LambdaStage& stageutil::lambda(LambdaContext& lambdaContext)
{
	return LambdaStage::make(lambdaContext);
}

ForEach& stageutil::foreach()
{
	return ForEach::make();
}

Collect& stageutil::collect()
{
	return Collect::make();
}

Chunk& stageutil::chunk(Func& key)
{
	return Chunk::make(key);
}

Chunk& stageutil::chunk()
{
	return Chunk::make();
}

GetItem& stageutil::get(seq_int_t idx)
{
	return GetItem::make(idx);
}

Serialize& stageutil::ser(std::string filename)
{
	return Serialize::make(std::move(filename));
}

Deserialize& stageutil::deser(types::Type& type, std::string filename)
{
	return Deserialize::make(&type, std::move(filename));
}

ExprStage& stageutil::expr(Expr *expr)
{
	return ExprStage::make(expr);
}

CellStage& stageutil::cell(Cell *cell)
{
	return CellStage::make(cell);
}

AssignStage& stageutil::assign(Cell *cell, Expr *value)
{
	return AssignStage::make(cell, value);
}

AssignIndexStage& stageutil::assignindex(Expr *array, Expr *idx, Expr *value)
{
	return AssignIndexStage::make(array, idx, value);
}

AssignMemberStage& stageutil::assignmemb(Cell *cell, seq_int_t idx, Expr *value)
{
	return AssignMemberStage::make(cell, idx, value);
}

Capture& stageutil::capture(void *addr)
{
	return Capture::make(addr);
}

Source& stageutil::source()
{
	return Source::make({});
}

If& stageutil::ifstage()
{
	return If::make();
}

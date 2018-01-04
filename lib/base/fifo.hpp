/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2018 Icinga Development Team (https://www.icinga.com/)  *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef FIFO_H
#define FIFO_H

#include "base/i2-base.hpp"
#include "base/stream.hpp"

namespace icinga
{

/**
 * A byte-based FIFO buffer.
 *
 * @ingroup base
 */
class FIFO final : public Stream
{
public:
	DECLARE_PTR_TYPEDEFS(FIFO);

	static const size_t BlockSize = 512;

	~FIFO() override;

	size_t Peek(void *buffer, size_t count, bool allow_partial = false) override;
	size_t Read(void *buffer, size_t count, bool allow_partial = false) override;
	void Write(const void *buffer, size_t count) override;
	void Close() override;
	bool IsEof() const override;
	bool SupportsWaiting() const override;
	bool IsDataAvailable() const override;

	size_t GetAvailableBytes() const;

private:
	char *m_Buffer{nullptr};
	size_t m_DataSize{0};
	size_t m_AllocSize{0};
	size_t m_Offset{0};

	void ResizeBuffer(size_t newSize, bool decrease);
	void Optimize();
};

}

#endif /* FIFO_H */

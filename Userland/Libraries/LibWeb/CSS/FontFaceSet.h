/*
 * Copyright (c) 2024, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/Set.h>
#include <LibJS/Runtime/SetIterator.h>
#include <LibWeb/Bindings/FontFaceSetPrototype.h>
#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/CSS/FontFace.h>

namespace Web::CSS {

class FontFaceSet final : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(FontFaceSet, Bindings::PlatformObject);
    JS_DECLARE_ALLOCATOR(FontFaceSet);

public:
    [[nodiscard]] static JS::NonnullGCPtr<FontFaceSet> construct_impl(JS::Realm&, Vector<JS::Handle<FontFace>> const& initial_faces);
    [[nodiscard]] static JS::NonnullGCPtr<FontFaceSet> create(JS::Realm&);
    virtual ~FontFaceSet() override = default;

    JS::NonnullGCPtr<JS::Set> set_entries() const { return m_set_entries; }

    JS::NonnullGCPtr<FontFaceSet> add(JS::Handle<FontFace>);
    bool delete_(JS::Handle<FontFace>);
    void clear();
    JS::ThrowCompletionOr<JS::NonnullGCPtr<JS::Promise>> load(String const& font, String const& text);

    JS::NonnullGCPtr<JS::Promise> ready() const;
    Bindings::FontFaceSetLoadStatus status() const { return m_status; }

private:
    FontFaceSet(JS::Realm&, JS::NonnullGCPtr<WebIDL::Promise> ready_promise, JS::NonnullGCPtr<JS::Set> set_entries);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    JS::NonnullGCPtr<JS::Set> m_set_entries;
    JS::GCPtr<WebIDL::Promise> m_ready_promise; // [[ReadyPromise]]

    Bindings::FontFaceSetLoadStatus m_status { Bindings::FontFaceSetLoadStatus::Loading };
};

}
